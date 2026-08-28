import Radio from "../models/radio.model.js";

export const createRadioScan = async (req,res) => {
    try {
        const radio = await Radio.create(req.body);
        res.status(201).json({
            message: "radio data saved",
            data: data
        });
        
    } catch (err) {
        res.status(500).json({
            message: "failed to save radio data",
            error: err.message
        });
    }
}

export const getRadioScan = async (req,res) => {
    try {
        const data = await Radio.find().sort({ createdAt: -1 });
        res.status(200).json({
            data: data
        });
    } catch (err) {
        res.status(500).json({
            message: "failed to get radio data",
            error: err.message
        });
    }
}