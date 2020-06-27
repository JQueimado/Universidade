import React, { Component } from "react";
import JwtClient from "./Controlers/Jwt.controler.js";

class App extends Component {
    constructor(props) {
        super(props);

        this.state = {
            jwtClient: new JwtClient(),
        };
    }

    render() {
        return (
            <div className="App">
                <button
                    onClick={() => {
                        console.log(
                            this.state.jwtClient.authenticate("admin", "admin")
                        );
                    }}
                >
                    It hurts
                </button>
            </div>
        );
    }
}

export default App;
