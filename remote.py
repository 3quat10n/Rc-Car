import socket
import pygame

pygame.init()

screen = pygame.display.set_mode((800,500))
pygame.display.set_caption("rc Car")
clock = pygame.time.Clock()

ip = "192.168.4.1"
port = 4444

try:
    print(f"[+]Connecting to {ip}:{port}...")
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
    s.connect((ip, port))
    print(f"[+]Connected.")
except Exception as e:
    print(f"[-]Connection Failled {ip}:{port}...")
    print(e)
    exit(0)


def send_commond(data):
    try:
        s.send(data.encode())
    except Exception as e:
        print(e)
        pass
        
def print_text(text,x,y):
    img = pygame.font.SysFont("Arial",30).render(text,1,(250,250,250))
    screen.blit(img,(x,y))

run = 1
key = ""
while run:
    clock.tick(60)
    screen.fill((0,0,0))
    
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            run = 0
    
    keys = pygame.key.get_pressed()
    print_text(f"{key} Is Pressed",400,250)
    if keys[pygame.K_z]:
        send_commond("z")
        key = "Z"

    elif keys[pygame.K_q]:
        send_commond("q")
        key = "Q"

    elif keys[pygame.K_d]:
        send_commond("d")
        key = "D"

    elif keys[pygame.K_s]:
        send_commond("s")
        key = "S"

    elif keys[pygame.K_a]:
        send_commond("a")
        key = "A"

    elif keys[pygame.K_e]:
        send_commond("e")
        key = "E"

    else:
        send_commond("n")
        key = "n"

    pygame.display.flip()
pygame.quit()
