// Funzione per caricare i dati JSON (navbar e footer)
async function loadData() {
    try {
        const response = await fetch('./carrello.json');
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

// Funzione per estrarre il prezzo da una stringa (es. "€10,99")
function parsePrice(priceStr) {
    const priceNumber = parseFloat(priceStr.replace(/[^\d.-]/g, ''));
    return isNaN(priceNumber) ? 0 : priceNumber;
}

// Funzione per renderizzare il carrello
function renderCart() {
    const cartItemsContainer = document.getElementById('cart-items');
    const cartItems = JSON.parse(localStorage.getItem('cartItems')) || [];

    cartItemsContainer.innerHTML = '';  // Pulisce il contenitore del carrello

    if (cartItems.length === 0) {
        cartItemsContainer.innerHTML = '<p>Il carrello è vuoto.</p>';
    } else {
        let total = 0;  // Variabile per sommare il totale senza sconto
        let itemCount = 0; // Conta i prodotti nel carrello

        cartItems.forEach((item, index) => {
            const price = parsePrice(item.price);

            const itemCard = `
                <div class="col-md-4">
                    <div class="card mb-4 h-100">
                        <img src="${item.image}" class="card-img-top" alt="${item.title}">
                        <div class="card-body d-flex flex-column">
                            <h5 class="card-title">${item.title}</h5>
                            <p class="card-text">${price.toFixed(2)} €</p>
                            <div class="d-flex align-items-center">
                                <span class="fw-bold me-2">Quantità:</span>
                                <span class="badge bg-secondary px-3 py-2">${item.quantity}</span>
                            </div>
                            <button class="btn btn-danger remove-item mt-3" data-index="${index}">Rimuovi</button>
                        </div>
                    </div>
                </div>
            `;
            cartItemsContainer.innerHTML += itemCard;

            total += price * item.quantity;  // Somma il totale
            itemCount += item.quantity; // Conta gli articoli nel carrello
        });

        let discount = 0;
        if (itemCount >= 3) {
            discount = total * 0.15;
            total -= discount;
        }

        const totalContainer = `
            <div class="col-12 mt-4 text-end">
                ${itemCount >= 3 ?
                `<h4 class="text-decoration-line-through text-dark">Totale: €${(total + discount).toFixed(2)}</h4>` :
                `<h4>Totale: €${total.toFixed(2)}</h4>`}
                ${itemCount >= 3 ? `<h5>Totale (15% di sconto su acquisti di 3 o più prodotti): €${total.toFixed(2)}</h5>` : ''}
            </div>
        `;
        cartItemsContainer.innerHTML += totalContainer;

        // Gestore di eventi per i pulsanti di rimozione
        const removeButtons = document.querySelectorAll('.remove-item');
        removeButtons.forEach(button => {
            button.addEventListener('click', (event) => {
                const index = event.target.getAttribute('data-index');
                cartItems.splice(index, 1);
                localStorage.setItem('cartItems', JSON.stringify(cartItems));
                renderCart();  // Rende il carrello senza ricaricare la pagina
            });
        });
    }
}

// Funzione per aggiungere un prodotto al carrello
function addToCart(newItem) {
    const cartItems = JSON.parse(localStorage.getItem('cartItems')) || [];
    const existingItemIndex = cartItems.findIndex(item => item.title === newItem.title);
    if (existingItemIndex > -1) {
        cartItems[existingItemIndex].quantity += newItem.quantity;
    } else {
        cartItems.push(newItem);
    }
    localStorage.setItem('cartItems', JSON.stringify(cartItems));
    renderCart();  // Rende il carrello dopo aver aggiunto un nuovo prodotto
}

// Event listener per il caricamento della pagina
document.addEventListener('DOMContentLoaded', () => {
    loadData(); // Carica navbar e footer
    renderCart(); // Rende il carrello all'avvio

    // Esempio di aggiunta prodotto al carrello
    document.getElementById('add-to-cart').addEventListener('click', () => {
        const newItem = {
            title: "Esempio di Prodotto",
            image: "https://via.placeholder.com/200",
            price: "€20,00",
            quantity: 1
        };
        addToCart(newItem);
    });
});

