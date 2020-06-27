class JwtClient {
    constructor() {
        this.token = "";

        this.getToken = this.getToken.bind();
        this.authenticate = this.authenticate.bind();
    }

    getToken() {
        return this.token;
    }

    authenticate(username, password) {
        var body = {
            username: username,
            password: password,
        };

        var myHeaders = new Headers({
            "Content-Type": "application/json;charset=utf-8",
        });

        fetch("https://localhost:8443/login", {
            method: "POST",
            headers: myHeaders,
            mode: "cors",
            cache: "default",
            body: JSON.stringify(body),
        })
            .then((response) => response.json())
            .then((token) => (this.token = token.token));
    }
}

export default JwtClient;
