const React = require("react");
const ReactDOM = require("react-dom");
//const client = require("./client");

//Dependecies
import { BrowserRouter as Router, Route, Link } from "react-router-dom";

import Home from "./componnets/Home.component";
import Login from "./componnets/Login.component";

/*
class Employee extends React.Component {
    render() {
        return (
            <tr>
                <td>{this.props.employee.firstName}</td>
                <td>{this.props.employee.lastName}</td>
                <td>{this.props.employee.description}</td>
            </tr>
        );
    }
}

class EmployeeList extends React.Component {
    render() {
        const employees = this.props.employees.map((employee) => (
            <Employee key={employee._links.self.href} employee={employee} />
        ));
        return (
            <table>
                <tbody>
                    <tr>
                        <th>First Name</th>
                        <th>Last Name</th>
                        <th>Description</th>
                    </tr>
                    {employees}
                </tbody>
            </table>
        );
    }
}
*/

class App extends React.Component {
    constructor(props) {
        super(props);
        this.state = {
            /*employees: []*/
        };
    }
    /*
    componentDidMount() {
        client({ method: "GET", path: "/api/employees" }).done((response) => {
            this.setState({ employees: response.entity._embedded.employees });
        });
    }
    */
    render() {
        //return <EmployeeList employees={this.state.employees} />;
        return (
            <Router>
                <Route path="/" exact component={Home} />
                <Route path="/login" exact component={Login} />
            </Router>
        );
    }
}

// Main call
ReactDOM.render(<App />, document.getElementById("react"));
