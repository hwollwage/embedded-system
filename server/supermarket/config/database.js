import "dotenv/config";
import mongoose from "mongoose";

const connectDB = async () => {
    try {
        await mongoose.connect(process.env.MONGO_URI);
        console.log("mongodb connected");

    }catch(err) {
        console.error("mongodb conn failed:", err.message);
        process.exit(1);
    }
};

export default connectDB;