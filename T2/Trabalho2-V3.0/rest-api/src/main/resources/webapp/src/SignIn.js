import React, { Component } from "react";

class SignIn extends Component {
    constructor(props) {
        super(props);
    }

    render() {
        return (
            <div>
                <button onClick={() => this.props.register("joao", "password")}>
                    {" "}
                    REGISTERTEST{" "}
                </button>
            </div>
        );
    }
}

export default SignIn;
