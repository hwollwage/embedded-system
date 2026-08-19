import mongoose from "mongoose";

const gasSchema = new mongoose.Schema({
    deviceId: {type:String, required: true, max:50, trim: true},
    gasValue: {type:Number, required: true},
    alarm: {type: Boolean, required: true},
    ipAddress: {type: String, required: true},
    wifiRSSI: {type: Number, required: true},
    uptime: {type: Number, required: true},
    freeHeap: {type: Number, required: true}
});

const Gas = mongoose.model("Gas", gasSchema);
export default Gas;