async function loadData() {
  try {
    const response = await fetch('../pages/archivio/archivio.json');
    const data = await response.json();

    // Carica le card
    loadCards(data.games);
  } catch (error) {
    console.error('Error loading the JSON data:', error);
  }
}

function loadCards(games) {
  const cardContainer = document.getElementById('card-container');

  // Genera le card
  games.forEach((game, index) => {
    const col = document.createElement('div');
    col.className = 'col-md-4';
    col.style.padding = '2%; margin: 0;';

    // Creazione lista edizioni
    const editionsList = game.editions.map(edition => `<li>${edition}</li>`).join('');

    col.innerHTML = `
      <div class="card" style="text-decoration: none; color: inherit;" data-index="${index}">
          <img src="${game.image}" class="card-img-top" alt="${game.title}">
          <div class="card-body">
              <h5 class="card-title">${game.title}</h5>
              <p class="card-text">${game.type}</p>
              <p class="card-text"><strong>${game.price}</strong></p>
              <ul class="card-text">${editionsList}</ul>
          </div>
      </div>
    `;

    // Aggiungi evento click sulla card
    col.querySelector('.card').addEventListener('click', () => {
      // Salva i dati della card nel localStorage
      localStorage.setItem('selectedCard', JSON.stringify(game));
      // Vai alla pagina
      window.location.href = './prodotto.php';
    });

    cardContainer.appendChild(col);
  });
}

window.onload = loadData;
