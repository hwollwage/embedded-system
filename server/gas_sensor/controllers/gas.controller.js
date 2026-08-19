import Gas from "../models/gas.model.js";

// POST CREATE
export const createGasData = async (req, res) => {
    try {
        const gas = await Gas.create(req.body);
        res.status(201).json({
            message: "gas data created",
            data: gas
        });

    } catch (err) {
        res.status(500).json({
            message: "failed to create gas data",
            error: err.message
        });
    }
}

// GET DATA
export const getGasData = async (req,res) => {
    try {
        const gasData = await Gas.find();

        res.status(200).json({
            message: "gas data retrieved",
            data: gasData
        });

    } catch (err) {
        res.status(500).json({
            message: "failed to get gas data",
            error: err.message
        });
    }
}

// DELETE DATA
export const deleteGasData = async (req,res) => {
    try {
        const { id } = req.params;
        const gas = await Gas.findByIdAndDelete(id);

        if(!gas) {
            res.status(404).json({
                message: "gas data not found"
            });
        }

        res.status(200).json({
            message: "data deleted",
            data: gas
        });

    } catch (err) {
        res.status(500).json({
            message: "failed to delete data",
            error: err.message
        });
    }
}

export const updateGasData = async (req,res) => {
    try {
        const { id } = req.params;
        const gas = await Gas.findByIdAndUpdate(
            // {_id: id},
            // req.body,
            // {returnDocument: "after"}
            id,
            req.body,
            {returnDocument: "after"}
        );

        if(!gas) {
            res.status(404).json({
                message: "data not found to be updated",
            });
        }

        res.status(200).json({
            message: "gas data updated",
            data: gas
        });

    } catch (err) {
        res.status(500).json({
            message: "failed to update gas data",
            error: err.message
        });
    }
}