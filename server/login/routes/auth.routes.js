const express = require("express");
const bcrypt = require("bcrypt");
const jwt = require("jsonwebtoken");

const User = require("../models/user.model");
import Test from "../models/test.model";

const router = express.Router();
const JWT_TOKEN = "prabowo-biji-satu";

router.post("/register", async (req, res) => {
    try {
        const { username, password } = req.body;
        const isUserExist = await User.findOne({ username });

        if (isUserExist) {
            return res.status(409).json({
                error: "username already exist"
            });
        }

        const hashedPassword = await bcrypt.hash(password, 10);
        const user = new User({
            username: username,
            password: hashedPassword
        });

        await user.save();

        res.json({
            message: "user registered"
        });

    } catch (err) {
        res.status(500).json({
            error: err.message
        });
    }
});

router.post("/login", async (req, res) => {
    try {
        const { username, password } = req.body;
        const user = await User.findOne({ username });
        if (!user) {
            return res.status(401).json({
                error: "invalid uname or pass"
            });
        }

        const isPassMatch = await bcrypt.compare(
            password,
            user.password
        );

        if (!isPassMatch) {
            return res.status(401).json({
                error: "invalide uname or pass"
            });
        }

        const token = jwt.sign(
            {
                userId: user._id,
                username: user.username
            },
            JWT_TOKEN,
            {
                expiresIn: "1h"
            }
        );

        res.json({
            message: "login successful",
            token: token
        });
    } catch (err) {
        res.status(500).json({
            error: err.message
        });
    }
})

module.exports = router;