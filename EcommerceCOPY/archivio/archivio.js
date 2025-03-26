async function loadData() {
  try {
    const response = await fetch('./archivio.json');
    const data = await response.json();

    // Carica la navbar
    loadNavbar(data.navbar);
    // Carica il footer
    loadFooter(data.footer);
    // Carica le card
    loadCards(data.games);
  } catch (error) {
    console.error('Error loading the JSON data:', error);
  }
}

function loadNavbar(navbarData) {
  const navbarContainer = document.getElementById('navbar-container');

  const links = navbarData.links.map(link => `
    <li class="nav-item">
      <a class="nav-link text-black" href="${link.href}">${link.text}</a>
    </li>
  `).join('');

  navbarContainer.innerHTML = `
    <nav class="navbar bg-black">
      <div class="container-fluid">
        <h1 class="navbar-brand">${navbarData.title}</h1>
        <button class="navbar-toggler" type="button" data-bs-toggle="offcanvas" data-bs-target="#offcanvasNavbar"
          aria-controls="offcanvasNavbar">
          <span class="navbar-toggler-icon"></span>
        </button>
        <div class="offcanvas offcanvas-end" tabindex="-1" id="offcanvasNavbar" aria-labelledby="offcanvasNavbarLabel">
          <div class="offcanvas-header" style="border-bottom: 1px solid black;">
            <h5 class="offcanvas-title text-black" id="offcanvasNavbarLabel">${navbarData.title}</h5>
            <button type="button" class="btn-close" data-bs-dismiss="offcanvas" aria-label="Close"></button>
          </div>
          <div class="offcanvas-body" style="text-align: center;">
            <ul class="navbar-nav justify-content-end flex-grow-1 pe-3">
              ${links}
            </ul>
          </div>
        </div>
      </div>
    </nav>
  `;
}

function loadFooter(footerData) {
  const footerContainer = document.getElementById('footer-container');

  footerContainer.innerHTML = `
    <footer>
      <div class="bg-black p-4 text-center">
        <p class="mb-2 text-white">${footerData.text}</p>
      </div>
    </footer>
  `;
}

function loadCards(games) {
  const cardContainer = document.getElementById('card-container');

  // Genera le card
  games.forEach((game, index) => {
    const col = document.createElement('div');
    col.className = 'col-md-4';
    col.style.padding = '2%; margin: 0;';

    col.innerHTML = `
      <div class="card" style="text-decoration: none; color: inherit;" data-index="${index}">
          <img src="${game.image}" class="card-img-top" alt="${game.title}">
          <div class="card-body">
              <h5 class="card-title">${game.title}</h5>
              <p class="card-text">${game.type}</p>
              <p class="card-text"><strong>${game.price}</strong></p>
          </div>
      </div>
    `;

    // Aggiungi evento click sulla card
    col.querySelector('.card').addEventListener('click', () => {
      // Salva i dati della card nel localStorage
      localStorage.setItem('selectedCard', JSON.stringify(game));
      // Vai alla pagina
      window.location.href = '../prodotto/prodotto.html';
    });

    cardContainer.appendChild(col);
  });
}

window.onload = loadData;