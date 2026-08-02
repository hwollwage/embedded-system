


async function getUser(id) {
    const response = await fetch(
        `https://jsonplaceholder.typicode.com/users/${id}`
    );

    if(!response.ok) {
        throw new Error("gagal mengambil data");
    }

    return await response.json();
}

async function getAlbums(albums) {
    const response = await fetch(
        `https://jsonplaceholder.typicode.com/albums/${albums}`
    );

    if(!response.ok) {
        throw new Error("failed get data");
    }

    return await response.json();
}

async function main() {
    try {
        const albums = await getAlbums(1);
        console.log("title : ", albums.title);
    } catch (error) {
        console.log(error.message);
    }
}

main();