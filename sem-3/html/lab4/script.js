// Elements for pokemon card
const image = document.getElementById("image");
const name = document.getElementById("name");
const weight = document.getElementById("weight");
const height = document.getElementById("height");
const types = document.getElementById("types");

// Elements for searchbar
const searchForm = document.getElementById("search-form");
const searchBar = document.getElementById("search-bar");

searchForm.addEventListener("submit", async (event) => {
	// Prevent Page from reloading (dumb form html idiot)
	event.preventDefault();

	let url = "https://pokeapi.co/api/v2/pokemon/" + searchBar.value.toLowerCase();

	try {
		const response = await fetch(url);
		
		if (!response.ok) {
			throw new Error('Response status: ${response.status}');
		}

		const json = await response.json();
		console.log(json);

		// Changing variables based on pulled information.
		name.textContent = json.name;
		weight.textContent = json.weight;
		height.textContent = json.height;

		// For each element(type) create a new row in the table.
		json.types.forEach((item) => {
			const li = document.createElement("li");
			li.textContent = item.type.name;
			types.appendChild(li);
		});

		image.src = json.sprites.front_default;

	} catch (error) {
		console.error("Error fetching data:", error);
	}
});
