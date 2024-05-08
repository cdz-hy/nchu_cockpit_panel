# include <stdio.h>
# include <malloc.h>

struct situation
{
	int army;
	int grain;
	int people;
};

void situation(void)
{
	
}

int main(void)
{
	int i;
	char ch;

	printf("按1开始游戏，按2保存游戏积分并退出游戏，按3进入菜单，按4查看得分，其他按键强制退出，可能导致游戏数据丢失：\n");
	scanf_s("%d", &i);

	printf("你是一位国王，你的国家周围有六个实力相匹敌的国家，你要利用你的智慧消灭他们，是战争还是外交？这都由你选择！\n");
	printf("按p键进入王国概况，其他任意键进入游戏\n");
	scanf("%c", &ch);

	if (ch == 'p')
		

	return 0;
}