import React, { Component } from "react";

class Home extends Component {
    render() {
        return (
            <div>
                <h2>Hello Shoppers!</h2>
                <p>
                    This app is a new game changer to supermarket shoppers in
                    your local town. Gone are the days that consumers feared
                    going shopping for the necessary itens,and comming home
                    infect with the new virus.{" "}
                </p>

                <p>
                    The app informs every consumer of the degree/level of
                    ocupation that a certain supermarket has. This way, the
                    problem of overcrowd can be avoided. The levels are in 4
                    categories:
                </p>

                <ol>
                    <li>Empty or with minimum ocupation</li>
                    <li>With people, but with enouth space</li>
                    <li>overcrowded</li>
                    <li>overcrowded, with a big queue</li>
                </ol>

                <div>
                    <button onClick={() => this.props.supers(1)}>
                        TESTSUPERGET
                    </button>
                </div>
            </div>
        );
    }
}

export default Home;
