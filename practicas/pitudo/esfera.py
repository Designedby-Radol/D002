import math

i = 1
while True :
    if i % 3 == 0: 
        break
    print(i)
    i+=1
    print(i)

# def print_circle(radius):
#     for y in range(-radius, radius + 1):
#         for x in range(-radius, radius + 1):
#             if math.sqrt(x**2 + y**2) <= radius:
#                 print("*", end="")
#             else:
#                 print(" ", end="")
#         print()  # Salto de línea después de cada fila

# # Tamaño del círculo
# radius = 10

# # Imprimir el círculo
# print_circle(radius)
 