import "dotenv/config";
import express from "express";
import mongoose from "mongoose";
import authRoutes from "./routes/auth.routes.js";
import userRoutes from "./routes/user.route.js";

const app = express();
app.use(express.json());

mongoose
    .connect("mongodb://root:123@127.0.0.1:27018/login_db?authSource=admin")
    .then(() => {
        console.log("mongodb connected");
    })
    .catch((err) => {
        console.log("error :",err);
    });

app.use("/auth", authRoutes);
app.use("/user", userRoutes);

app.listen(3000, () => {
    console.log("server run at 3000");
});