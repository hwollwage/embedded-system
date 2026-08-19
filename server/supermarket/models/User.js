import mongoose from "mongoose";

const userSchema = new mongoose.Schema({
    username: {
        type: String,
        required: true,
        unique: true,
        trim: true,
        minlength: 3,
        maxlength: 30
    },
    password: {
        type: String,
        required: true,
        select: false
    },
    email: {
        type: String,
        require: true,
        unique: true,
    },
    role: {
        type: String,
        enum: ["user", "admin",],
        default: "user"
    }   
});

const User = mongoose.model("User", userSchema);

export default User;