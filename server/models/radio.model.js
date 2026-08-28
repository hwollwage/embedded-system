import mongoose from "mongoose";

const radioSchema = new mongoose.Schema({
    deviceId: {type: String, required: true},
    result: [
        {
            channel: Number,
            hits: Number
        }
    ],
    bestChannel: {type: Number}
});

const Radio = mongoose.model("radioSchema", radioSchema);
export default Radio;
