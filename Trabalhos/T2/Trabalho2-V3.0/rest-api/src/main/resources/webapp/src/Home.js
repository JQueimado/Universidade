import React, { Component } from "react";
import Table from "react-bootstrap/Table";

const SuperMarket = (props) => {
    var status = "";

    if (props.market.empty_or_with_minimum_ocupation > 0)
        status +=
            "Empty or with minimum ocupation: " +
            props.market.empty_or_with_minimum_ocupation +
            " reports";

    if (props.market.with_people_but_with_enouth_space > 0)
        status +=
            "With people, but with enouth space: " +
            props.market.with_people_but_with_enouth_space +
            " reports";

    if (props.market.overcrowded > 0)
        status += "Overcrowded: " + props.market.overcrowded + " reports";

    if (props.market.overcrowded_with_a_big_queue > 0)
        status +=
            "Overcrowded, with a big queue: " +
            props.market.overcrowded_with_a_big_queue +
            " reports";

    if (status === "") status = "no recent reports";
    return (
        <tr>
            <td>{props.market.super_name}</td>
            <td>{status}</td>
        </tr>
    );
};

class Home extends Component {
    constructor(props) {
        super(props);

        this.state = { loaded: false };
    }

    listing() {
        return this.props.supersList.map((e, i) => {
            return <SuperMarket market={e} />;
        });
    }

    render() {
        return (
            <div>
                <h2>Hello Shoppers!</h2>
                <p>
                    This app is a new game changer to supermarket shoppers in
                    your local town. Gone are the days that consumers feared
                    going shopping for the necessary itens,and comming home
                    infect with the new virus.{" "}
                </p>

                <p>
                    The app informs every consumer of the degree/level of
                    ocupation that a certain supermarket has. This way, the
                    problem of overcrowd can be avoided. The levels are in 4
                    categories:
                </p>

                <ol>
                    <li>Empty or with minimum ocupation</li>
                    <li>With people, but with enouth space</li>
                    <li>overcrowded</li>
                    <li>overcrowded, with a big queue</li>
                </ol>

                <div>
                    <button onClick={() => this.props.supers(1)}>
                        Refresh
                    </button>

                    <Table striped bordered hover>
                        <thead>
                            <tr>
                                <th>Super Market Name</th>
                                <th>Ocupation</th>
                            </tr>
                        </thead>
                        <tbody>{this.listing()}</tbody>
                    </Table>
                </div>
            </div>
        );
    }
}

export default Home;
