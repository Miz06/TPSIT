document.addEventListener('DOMContentLoaded', () => {
  const cardData = JSON.parse(localStorage.getItem('selectedCard'));

  if (cardData) {
      document.querySelector('#game-title').textContent = cardData.title;
      document.querySelector('#game-type').textContent = cardData.type;
      document.querySelector('#game-image').src = cardData.image;
      document.querySelector('#game-price').textContent = cardData.price;
      document.querySelector('#game-text').textContent = cardData.text;
  }

  // Aggiungi un gestore di eventi per il pulsante "Aggiungi al carrello"
  const addToCartButton = document.querySelector('.btn-dark');
  addToCartButton.addEventListener('click', () => {
      // Recupera i dati del prodotto
      const cartItems = JSON.parse(localStorage.getItem('cartItems')) || [];
      
      // Aggiungi il prodotto al carrello
      cartItems.push(cardData);
      
      // Salva il carrello nel localStorage
      localStorage.setItem('cartItems', JSON.stringify(cartItems));

      window.location.href = '../carrello/carrello.html'; // Cambia 'carrello.html' con il percorso corretto
  });
});