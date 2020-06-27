import axios from "axios";

class JwtClient {
    constructor() {
        this.authenticate = this.authenticate.bind();
        axios.defaults.baseURL = "https://localhost:8443/";
        axios.defaults.headers.post["Content-Type"] =
            "application/json;charset=utf-8";
    }

    authenticate(username, password) {
        var token = "no token";

        var body = {
            username: username,
            password: password,
        };

        axios
            .post("/login", body)
            .then((response) => (token = response.data.token));
        /*
        fetch("https://localhost:8443/login", {
            method: "POST",
            headers: myHeaders,
            mode: "cors",
            cache: "default",
            body: JSON.stringify(body),
        })
            .then((response) => response.json())
            .then((token) => (this.token = token.token));
        */
        return token;
    }
}

export default JwtClient;
