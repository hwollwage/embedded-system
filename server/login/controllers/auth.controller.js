import bcrypt from "bcrypt";
import jwt from "jsonwebtoken";

import User from "../models/user.model.js";

export const register = async (req,res) => {
    try {
        const {username, password} = req.body;
        const isUserExist = await User.findOne({username});

        if(isUserExist) {
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
    }catch(err) {
        res.status(500).json({
            error: err.message
        });
    }
}

export const login = async (req,res) => {
    try {
        const {username, password} = req.body;
        const user = await User
                                .findOne({username})
                                .select("+password");
        
        if(!user) {
            return res.status(401).json({
                error: "invalide uname or pass"
            });
        }

        const isPassMatch = await bcrypt.compare(password, user.password);
        if(!isPassMatch) {
            return res.status(401).json({
                error: "invalid uname or pass"
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
        });

    }catch(err) {
        res.status(500).json({
            error: err.message
        });
    }
}
