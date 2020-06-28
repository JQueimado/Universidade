import React, { Component } from "react";
import axios from "axios";
import SuperMarketList from "./Components/SupermarketList.component";

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

        //Axios Setup
        this.authenticate = this.authenticate.bind();
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
                this.setState({ token: response.data.token });
            })
            .catch((err) => console.log(err));
    }

    render() {
        return (
            <div className="App">
                <button onClick={this.authenticate}>It hurts</button>

                <SuperMarketList />
            </div>
        );
    }
}

export default App;
