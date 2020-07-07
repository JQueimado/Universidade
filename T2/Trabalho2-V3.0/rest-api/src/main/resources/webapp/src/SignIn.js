import React, { Component } from "react";

class SignIn extends Component {
    constructor(props) {
        super(props);
    }

    render() {
        return (
            <div>
                <button
                    onClick={() => {
                        this.props.login("admin", "admin");
                    }}
                >
                    LOGINTEST
                </button>
                <button
                    onClick={() => {
                        this.props.logout();
                    }}
                >
                    LOGOUTTEST
                </button>
            </div>
        );
    }
}

export default SignIn;
