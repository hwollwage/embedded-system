import bcrypt from "bcrypt";
import jwt from "jsonwebtoken";

import User from "../models/User.js"

export const register = async (req, res) => {
    try {
        const {username, password} = req.body;
        const isUserExist = await User.findOne({username});

        if(isUserExist) {
            return res.json({
                error: "user already exist"
            });
        }

        const hashedPassword = bcrypt.hash(password, 10);

        const user = new User({
            username: username,
            password: hashedPassword
        });

        await user.save();
    
    } catch(err) {
        res.status({
            error: err.message
        });
    }
}

export const login = async (req, res) => {
    try {
        const {username, password} = req.body;
        const user = await User
                                .findOne({username})
                                .select("+password");
        
        if(!user) {
            return res.status(401).json({
                error: "invalid user or pass"
            });
        }

        const isPassMatch = bcrypt.compare(password, user.password);
        if(!isPassMatch) {
            return res.status(401).json({
                error: "invalid user or pass (ispassmatch)"
            });
        }

        const token = jwt.sign(
            {
                userId: user._id,
                username: user.username
            },
            process.env.JWT_SECRET,
            {
                expiresIn: "1h"
            }
        );

        res.json({
            message: "login successful",
            token
        })

    }catch(err) {
        res.status(500).json({
            error: err.message
        });
    }
}