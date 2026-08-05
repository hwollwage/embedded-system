const { WebSocketServer } = require("ws");
const wss = new WebSocketServer({ port: 8081 });

console.log("Server listening on ws://localhost:8081");

wss.on("connection", (ws) => {
    console.log("Client connected");
    ws.send("Welcome!");

    ws.on("message", (message) => {
        console.log(message.toString());
        ws.send(message.toString());
    });

    ws.on("close", () => {
        console.log("Client disconnected");
    });
});