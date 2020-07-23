import React, { Component } from "react";
import { Link } from "react-router-dom";

class Home extends Component {
    constructor(props) {
        super(props);
        this.state = {};
    }
    render() {
        return (
            <div>
                Home Page
                <Link to="/login">
                    <div>login</div>
                </Link>
            </div>
        );
    }
}

export default Home;
