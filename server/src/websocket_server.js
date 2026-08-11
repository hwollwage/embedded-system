const { WebSocketServer } = require("ws");
const express = require("express");

const app = express();
const wss = new WebSocketServer({ port: 8081 });

let lastMessage = null;

wss.on("connection", (ws) => {
    console.log("WebSocket client connected");

    ws.send("Welcome!");

    ws.on("message", (message) => {
        lastMessage = message.toString();
        console.log("WebSocket message:", lastMessage);
        ws.send(lastMessage);
    });

    ws.on("close", () => {
        console.log("WebSocket client disconnected");
    });
});

app.get("/", (req, res) => {
    res.json({
        message: lastMessage
    });
});

app.listen(3000, () => {
    console.log("Express listening on http://localhost:3000");
    console.log("WebSocket listening on ws://localhost:8081");
});