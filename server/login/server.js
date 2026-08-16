const express = require("express");
const mongoose = require("mongoose");
const authRoutes = require("./routes/auth.routes");

const app = express();

app.use(express.json());

mongoose
    .connect("mongodb://root:123@127.0.0.1:27018/login_db?authSource=admin")
    .then(() => {
        console.log("mongo connected");
    })
    .catch((err) => {
        console.log("error : ", err);
    });

app.use("/auth", authRoutes);
app.listen(3000, () => {
    console.log("port 3000");
});