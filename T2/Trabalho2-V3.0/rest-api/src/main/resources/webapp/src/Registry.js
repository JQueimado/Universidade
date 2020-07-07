import React, { Component } from "react";
import Table from "react-bootstrap/Table";

const RegistryComp = (props) => {
    var status = "";

    if (props.reg.level === 1) status = "Empty or with minimum ocupation";
    if (props.reg.level === 2) status = "With people, but with enouth space";
    if (props.reg.level === 3) status = "Overcrowded";
    if (props.reg.level === 4) status = "Overcrowded, with a big queue";

    return (
        <tr>
            <td>{props.reg.super_name}</td>
            <td>{status}</td>
            <td>
                {" "}
                <button
                    onClick={() => {
                        props.remove(props.reg.id);
                    }}
                >
                    Delete
                </button>{" "}
            </td>
        </tr>
    );
};

const NewRegistry = (props) => {
    return (
        <div>
            {" "}
            <input onChange={props.onSuperChange}></input>
            <input onChange={props.onLevelChange}></input>
            <button onClick={props.onSubmit}>Submit</button>
        </div>
    );
};

class Registry extends Component {
    constructor(props) {
        super(props);

        this.onLevelChange = this.onLevelChange.bind(this);
        this.onSubmit = this.onSubmit.bind(this);
        this.onSuperChange = this.onSuperChange.bind(this);
    }

    state = { supername: "", level: 0 };

    listing() {
        return this.props.regListing.map((e, i) => {
            return <RegistryComp remove={this.props.removeRegistry} reg={e} />;
        });
    }

    onSuperChange(e) {
        this.setState({ supername: e.target.value });
    }

    onLevelChange(e) {
        this.setState({ level: e.target.value });
    }

    onSubmit() {
        this.props.createRegistry(this.state.supername, this.state.level);
    }

    render() {
        return (
            <div>
                <h2>Ocupation Registry</h2>

                <button
                    onClick={() => {
                        this.props.createRegistry("lidl", 3);
                    }}
                    class="button button1"
                >
                    Create Registry
                </button>

                <NewRegistry
                    onSubmit={this.onSubmit}
                    onSuperChange={this.onSuperChange}
                    onLevelChange={this.onLevelChange}
                />

                <button onClick={this.props.regs}> Refresh </button>

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
        );
    }
}

export default Registry;
