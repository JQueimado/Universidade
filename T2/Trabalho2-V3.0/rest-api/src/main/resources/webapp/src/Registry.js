import React, { Component } from "react";

class Registry extends Component {
    render() {
        return (
            <div>
                <h2>Ocupation Registry</h2>

                <button
                    onClick={() => {
                        this.props.createRegistry("lidl", 3);
                    }}
                    class="button button1"
                >
                    Create Registry
                </button>
                <button onClick={this.props.regs} class="button button1">
                    Show Registry
                </button>
            </div>
        );
    }
}

export default Registry;
