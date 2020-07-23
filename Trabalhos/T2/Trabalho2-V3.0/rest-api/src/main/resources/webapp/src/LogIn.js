import React, { Component } from "react";

const Form = (props) => {
    return (
        <div>
            <h3> Username </h3>
            <input onChange={props.onUserChange}></input>
            <h3> Password </h3>
            <input onChange={props.onPasswordChange} type="password"></input>
            <button onClick={props.onSubmit}> Submit </button>
        </div>
    );
};

class LogIn extends Component {
    constructor(props) {
        super(props);

        this.state = { username: "", password: "" };

        this.onUserChange = this.onUserChange.bind(this);
        this.onPasswordChange = this.onPasswordChange.bind(this);
        this.onSubmit = this.onSubmit.bind(this);
    }

    onUserChange(e) {
        this.setState({ username: e.target.value });
    }

    onPasswordChange(e) {
        this.setState({ password: e.target.value });
    }

    onSubmit() {
        this.props.login(this.state.username, this.state.password);
    }

    render() {
        return (
            <div>
                {!this.props.loged ? (
                    <Form
                        onPasswordChange={this.onPasswordChange}
                        onUserChange={this.onUserChange}
                        onSubmit={this.onSubmit}
                    ></Form>
                ) : null}
            </div>
        );
    }
}

export default LogIn;
