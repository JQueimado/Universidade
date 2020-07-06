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
        };

        //Method Binding
        this.login = this.login.bind(this);

        //Axios
        axios.defaults.baseURL = config.api;
        axios.defaults.headers.post["Content-Type"] =
            "application/json;charset=utf-8";

        //Testing
        this.login("admin", "admin");
    }

    //Methods
    login(username, password) {
        if (this.state.logedin) return;

        let body = {
            username: username,
            password: password,
        };

        axios
            .post("/login", body)
            .then((response) => {
                this.setState({ token: response.data.token, logedin: true });
            })
            .catch((err) => console.log(err));
    }

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
                        <Route path="/signin" component={SignIn} />
                        <Route path="/login" component={LogIn} />
                        <Route path="/contact" component={Contact} />
                    </div>
                </div>
            </HashRouter>
        );
    }
}

export default Main;
