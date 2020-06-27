import React, { Component } from "react";
import { BrowserRouter as Router, Route, Link } from "react-router-dom";
import Home from "./Components/Home.component.jsx";
import JwtClient from "./Controlers/Jwt.controler.js";

class App extends Component {
    constructor(props) {
        super(props);
        this.jwtClient = new JwtClient();

        this.state = {
            token: "no token",
        };
    }

    render() {
        return (
            <Router>
                <div className="App">
                    <label>{this.state.token}</label>

                    <button
                        onClick={() => {
                            this.jwtControler
                                .authenticate("admin", "admin")
                                .then(
                                    this.setState({
                                        token: this.state.jwtControler.getToken(),
                                    })
                                );
                        }}
                    >
                        It hurts
                    </button>
                </div>
                <Link to="/login"> login </Link>
                <Route
                    path="/login"
                    exact
                    component={() => (
                        <Home jwtControler={this.state.jwtControler} />
                    )}
                />
            </Router>
        );
    }
}

export default App;
