const express = require("express");
const mongoose = require("mongoose");

const app = express();

app.use(express.json());

const userSchema =  new mongoose.Schema({
    name: String,
    age: Number,
    email: String
});

const User = mongoose.model("User", userSchema);

mongoose
    .connect("mongodb://127.0.0.1:27017/express_db")
    .then(() => {
        console.log("mongo db connected");

        app.listen(3000, () => {
            console.log("server running in port 3000");
        });
    })
    .catch((err) => {
        console.log("mongodb connection FAILED");
    });

app.post(`/users`, async (req, res) => {
    const user = new User({
        name: req.body.name,
        age: req.body.age,
        email: req.body.email
    });

    await user.save();
    res.json(user);
});

app.get(`/users`, async (req, res) => {
    const users = await User.find();
    res.json(users);
});