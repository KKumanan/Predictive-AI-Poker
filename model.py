import pandas as pd
import numpy as np
import tensorflow as tf
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense

data = pd.read_csv('poker_hands.csv')


X = data[['value1', 'suit1', 'value2', 'suit2']].values
y = data['outcome'].values

X = X / [12, 3, 12, 3]

model = Sequential([
    Dense(128, activation='relu', input_shape=(4,)),
    Dense(64, activation='relu'),
    Dense(32, activation='relu'),
    Dense(1, activation='sigmoid')
])

model.compile(optimizer='adam', loss='binary_crossentropy', metrics=['accuracy'])

model.fit(X, y, epochs=5, batch_size=64, validation_split=0.2)

model.save("poker_hand_probability_model.h5")



example_hand = np.array([[0, 0, 12, 1]])
example_hand = example_hand / [12, 3, 12, 3]
probability = model.predict(example_hand)

print(f"Probability of winning with the hand {example_hand}: {probability[0][0]:.2f}")
