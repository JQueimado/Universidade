import React, { Component } from "react";
import Table from "react-bootstrap/Table";
import axios from "axios";

const SuperMarket = (props) => {
    return (
        <tr>
            <td>{props.market.name}</td>
        </tr>
    );
};

class SuperMarketList extends Component {
    constructor(props) {
        super(props);
        this.state = { superMarkets: [], init_once: false };

        this.getallSuperMarkets();

        //Binding
        this.listing = this.listing.bind(this);
        this.getallSuperMarkets = this.getallSuperMarkets.bind(this);
    }

    getallSuperMarkets() {
        axios
            .get("/supermarkets")
            .then((response) => this.setState({ superMarkets: response.data }))
            .catch((err) => console.log(err));
    }

    listing() {
        return this.state.superMarkets.map((market, i) => {
            return <SuperMarket market={market} key={i} />;
        });
    }

    render() {
        return (
            <div>
                <button onClick={this.getallSuperMarkets}>Refresh</button>
                <Table striped bordered hover>
                    <thead>
                        <tr>
                            <th>Super Market Name</th>
                        </tr>
                    </thead>
                    <tbody>{this.listing()}</tbody>
                </Table>
            </div>
        );
    }
}

export default SuperMarketList;
