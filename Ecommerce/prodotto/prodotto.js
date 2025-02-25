document.addEventListener('DOMContentLoaded', () => {
  const cardData = JSON.parse(localStorage.getItem('selectedCard'));

  if (cardData) {
    document.querySelector('#game-title').textContent = cardData.title;
    document.querySelector('#game-type').textContent = cardData.type;
    document.querySelector('#game-image').src = cardData.image;
    document.querySelector('#price-value').textContent = cardData.price;
    document.querySelector('#game-text').textContent = cardData.text;
  }

  // logica incrementa/decrementa
  const quantityInput = document.querySelector('#quantity');
  const incrementButton = document.querySelector('#increment');
  const decrementButton = document.querySelector('#decrement');

  incrementButton.addEventListener('click', () => {
    quantityInput.value = parseInt(quantityInput.value) + 1;
  });

  decrementButton.addEventListener('click', () => {
    if (parseInt(quantityInput.value) > 1) {
      quantityInput.value = parseInt(quantityInput.value) - 1;
    }
  });

  // logica aggiungi al carrello
  const addToCartButton = document.querySelector('.btn-dark');
  addToCartButton.addEventListener('click', () => {
    const quantity = quantityInput.value;

    if (quantity < 1) {
      alert('La quantità deve essere almeno 1.');
      return;
    }

    const productWithQuantity = { ...cardData, quantity: parseInt(quantity) };

    const cartItems = JSON.parse(localStorage.getItem('cartItems')) || [];

    // Verifica se il prodotto esiste già nel carrello
    const existingItemIndex = cartItems.findIndex(item => item.title === productWithQuantity.title);
    if (existingItemIndex > -1) {
      // Se il prodotto esiste già, somma la quantità
      cartItems[existingItemIndex].quantity += productWithQuantity.quantity;
    } else {
      // Altrimenti, aggiungi il nuovo prodotto
      cartItems.push(productWithQuantity);
    }

    // Salva il carrello aggiornato nel localStorage
    localStorage.setItem('cartItems', JSON.stringify(cartItems));

    // Redirect alla pagina del carrello
    window.location.href = '../carrello/carrello.html';
  });
});

// Funzione per caricare i dati JSON (navbar e footer)
async function loadData() {
  try {
      const response = await fetch('./prodotto.json');
      const data = await response.json();

      // Carica la navbar
      loadNavbar(data.navbar);
      // Carica il footer
      loadFooter(data.footer);
  } catch (error) {
      console.error('Error loading the JSON data:', error);
  }
}

// Funzione per caricare la navbar
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

// Funzione per caricare il footer
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

// Event listener per il caricamento della pagina
document.addEventListener('DOMContentLoaded', () => {
  loadData();
});

