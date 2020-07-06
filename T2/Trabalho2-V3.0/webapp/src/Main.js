import React, { Component } from "react";
import {
  Route,
  NavLink,
  HashRouter
} from "react-router-dom";
import Home from "./Home";
import Registry from "./Registry";
import SignIn from "./SignIn"
import LogIn from "./LogIn"
import Contact from "./Contact";
 
class Main extends Component {
  render() {
    return (
      <HashRouter>
        <div>
          <h1>Ocupação de Espaços Comerciais</h1>
          
          <ul className="header">
            <li><NavLink exact to="/home">Home</NavLink></li>
            <li><NavLink to="/registry">Registry</NavLink></li>
            <li><NavLink to="/signin">Sign In</NavLink></li>
            <li><NavLink to="/login">Log In</NavLink></li>
            <li><NavLink to="/contact">Contact</NavLink></li>
          </ul>
          <div className="content">
            <Route exact path="/home" component={Home}/>
            <Route path="/registry" component={Registry}/>
            <Route path="/signin" component={SignIn}/>
            <Route path="/login" component={LogIn}/>
            <Route path="/contact" component={Contact}/>
          </div>
        </div>
      </HashRouter>
    );
  }
}
 
export default Main;