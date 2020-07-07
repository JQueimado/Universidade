import React, { Component } from "react";
import { Route, NavLink, HashRouter } from "react-router-dom";
import axios from "axios";

//Components
import Home from "./Home";
import Registry from "./Registry";
import SignIn from "./SignIn";
import LogIn from "./LogIn";
import Contact from "./Contact";

const config = {
    api: "https://localhost:8443",
};

class Main extends Component {
    constructor(props) {
        super(props);
        this.state = {
            token: "",
            logedin: false,
            superMarkets: [],
            registries: [],
        };

        //Method Binding
        this.login = this.login.bind(this);
        this.logout = this.logout.bind(this);
        this.getsupermarkets = this.getsupermarkets.bind(this);
        this.getregistries = this.getregistries.bind(this);

        //Axios
        axios.defaults.baseURL = config.api;
        axios.defaults.headers.post["Content-Type"] =
            "application/json;charset=utf-8";
    }

    //Methods
    //Login
    async login(username, password) {
        if (this.state.logedin) return false;

        var temp = false;

        let body = {
            username: username,
            password: password,
        };

        let response = await axios.post("/login", body);

        if (response.status == 200) {
            this.setState({
                token: "Bearer " + response.data.token,
                logedin: true,
            });
            console.log("got here");
            temp = true;
        }

        return temp;
    }

    //Logout
    async logout() {
        if (!this.state.logedin) return false;

        var temp = false;

        let response = await axios.post(
            "/logoutUser",
            { method: "logout" },
            { headers: { Authorization: this.state.token } }
        );

        if (response.status == 200) {
            this.setState({ token: "", logedin: false });
            temp = true;
        }

        return temp;
    }

    //Supermarkets
    async getsupermarkets(time) {
        return await axios
            .get("/supermarkets/" + time)
            .then((response) => {
                this.setState({ superMarkets: response.data });
                return true;
            })
            .catch((err) => {
                console.log(err);
                return false;
            });
    }

    //Registries
    async getregistries() {
        if (!this.state.logedin) return false;

        var temp = false;

        await axios
            .get("/registries/user", {
                headers: { Authorization: this.state.token },
            })
            .then((response) => {
                this.setState({ response: response.data });
                temp = true;
            })
            .catch((err) => {
                temp = false;
            });

        return temp;
    }

    //Render
    render() {
        return (
            <HashRouter>
                <div>
                    <h1>Ocupação de Espaços Comerciais</h1>

                    <ul className="header">
                        <li>
                            <NavLink exact to="/home">
                                Home
                            </NavLink>
                        </li>
                        <li>
                            <NavLink to="/registry">Registry</NavLink>
                        </li>
                        <li>
                            <NavLink to="/signin">Sign In</NavLink>
                        </li>
                        <li>
                            <NavLink to="/login">Log In</NavLink>
                        </li>
                        <li>
                            <NavLink to="/contact">Contact</NavLink>
                        </li>
                    </ul>
                    <div className="content">
                        <Route exact path="/home" component={Home} />
                        <Route path="/registry" component={Registry} />
                        <Route
                            path="/signin"
                            component={() => (
                                <SignIn
                                    login={(username, password) =>
                                        this.login(username, password)
                                    }
                                    logout={() => this.logout()}
                                />
                            )}
                        />
                        <Route path="/login" component={LogIn} />
                        <Route path="/contact" component={Contact} />
                    </div>
                </div>
            </HashRouter>
        );
    }
}

export default Main;
