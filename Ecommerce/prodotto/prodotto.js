document.addEventListener('DOMContentLoaded', () => {
    const cardData = JSON.parse(localStorage.getItem('selectedCard'));

    if (cardData) {
      document.querySelector('#game-title').textContent = cardData.title;
      document.querySelector('#game-type').textContent = cardData.type;
      document.querySelector('#game-image').src = cardData.image;
      document.querySelector('#game-price').textContent = cardData.price;
      document.querySelector('#game-text').textContent = cardData.text;
    }
  });