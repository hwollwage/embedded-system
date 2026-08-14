const express = require("express");
const mongoose = require("mongoose");
const bcrypt = require("bcrypt");

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

const userSchema = new mongoose.Schema({
    username: String,
    password: String
});

const User = mongoose.model("User", userSchema);

app.post("/register", async (req, res) => {
    const {username,password} = req.body;
    const hashedPassword = await bcrypt.hash(password,10);
    const user = new User({
        username: username,
        password: hashedPassword
    });

    await user.save();

    res.json({
        message: "user registered"
    });
});

app.listen(3000, () => {
    console.log("server run 3000");
});