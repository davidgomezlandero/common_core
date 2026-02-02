
COMPOSE_PATH = srcs/docker-compose.yml



all:
	docker compose -f $(COMPOSE_PATH) up -d --build

clean:
	docker compose -f $(COMPOSE_PATH) down

fclean:
	docker-compose -f $(COMPOSE_PATH) down
	docker stop $$(docker ps -qa) || true
	docker rm $$(docker ps -qa) || true
	docker rmi -f $$(docker images -qa) || true
	docker volume rm $$(docker volume ls -q) || true
	docker network rm $$(docker network ls -q) 2>/dev/null || true
re: fclean all

ps:
	docker compose -f $(COMPOSE_PATH) ps

.PHONE: all clean fclean re ps