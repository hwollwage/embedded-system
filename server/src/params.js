const express = require('express'); 
const app = express(); 

app.use(express.json()); 

const category_list = ["food", "drink", "snacks"];

app.listen(3000, () => { 
    console.log('server in port 3000'); 
}); 

app.get('/', (req, res) => { 
    res.send('test'); 
}); 

app.get('/search', (req, res, next) => {
    try {
        const category = req.query.category;
        if(category_list.includes(category)) {
            return res.status(200).json({
                "status": "200 success, category found",
                "category": category    
            });
        }

        return res.status(404).json({
            "status": "404 not found",
            "msg": `category '${category}' doesnt exist`
        });

    } catch(err) {
        console.log(`error : ${err}`);
        res.status(500).json({
            "error": err,
            "msg" : "something wrong"
        });
    }
});
