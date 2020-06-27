import React, { Component } from "react";

class Home extends Component {
    constructor(props) {
        super(props);
        this.state = { username: "", password: "", jwt: props.jwtControler };
        this.handleUsernameChange = this.handleUsernameChange.bind(this);
        this.handlePasswordChange = this.handlePasswordChange.bind(this);
        this.handleSubmit = this.handleSubmit.bind(this);
    }

    handleUsernameChange(event) {
        this.setState({ username: event.target.value });
    }

    handlePasswordChange(event) {
        this.setState({ password: event.target.value });
    }

    handleSubmit(event) {
        this.state.jwt.authenticate(this.username, this.password);
        console.log(this.state.jwt.getToken());
    }

    render() {
        return (
            <form onSubmit={this.handleSubmit}>
                <label>
                    Name:
                    <input
                        type="text"
                        value={this.state.username}
                        onChange={this.handleUsernameChange}
                    />
                </label>
                <label>
                    Password
                    <input
                        type="password"
                        value={this.state.password}
                        onChange={this.handlePasswordChange}
                    ></input>
                </label>
                <input type="submit" value="Submit" />
            </form>
        );
    }
}

export default Home;
