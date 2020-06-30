import React, { Component } from "react";
import axios from "axios";
import SuperMarketList from "./Components/SupermarketList.component";
import "./App.css";

class App extends Component {
    constructor(props) {
        super(props);

        this.state = {
            username: "admin",
            password: "admin",
            logedin: false,

            superMarkets: [],
            token: "",
        };

        //Bindig
        this.authenticate = this.authenticate.bind(this);
        this.onUserNameChange = this.onUserNameChange.bind(this);
        this.onUserPassChange = this.onUserPassChange.bind(this);
        this.logout = this.logout.bind(this);

        //Axios Setup
        axios.defaults.baseURL = "https://localhost:8443/";
        axios.defaults.headers.post["Content-Type"] =
            "application/json;charset=utf-8";
    }

    authenticate() {
        if (this.state.logedin) return;

        let body = {
            username: this.state.username,
            password: this.state.password,
        };

        axios
            .post("/login", body)
            .then((response) => {
                this.setState({ token: response.data.token, logedin: true });
            })
            .catch((err) => console.log(err));
    }

    //Login Form Methods
    onUserNameChange(event) {
        this.setState({ username: event.target.value });
    }

    onUserPassChange(event) {
        this.setState({ password: event.target.value });
    }

    onSubmit(event) {
        //this.authenticate();
        event.preventDefault();
    }

    logout() {
        this.setState({
            token: "",
            logedin: false,
            username: "",
            password: "",
        });

        axios
            .post(
                "/logoutUser",
                { method: "logout" },
                { headers: { Authorization: "Bearer " + this.state.token } }
            )
            .then((response) => {});
    }

    //Render
    render() {
        return (
            <div className="App">
                {
                    /*Login Form*/
                    this.state.logedin ? (
                        <div>
                            <h3>loged as {this.state.username}</h3>
                            <button onClick={this.logout}> Logout </button>
                        </div>
                    ) : (
                        <div>
                            <h3> Login: </h3>
                            <div>
                                Name:
                                <input
                                    type="text"
                                    onChange={this.onUserNameChange}
                                ></input>
                            </div>
                            <div>
                                Password:
                                <input
                                    type="password"
                                    onChange={this.onUserPassChange}
                                ></input>
                            </div>
                            <button onClick={this.authenticate}>Submit</button>
                        </div>
                    )
                }
                <h3> SuperMarkets </h3>
                <SuperMarketList />
            </div>
        );
    }
}

export default App;
