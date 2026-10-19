/**
 * @file    A10303-1_C04Q3.c
 * @brief   Q3. 자유 코드
 * @author  박철원 (Cheolwon Park)
 * @date    2024-03-23
 * 
 * @note    소스 코드에 사용된 scanf_s는 Visual Studio 이외의
 *	    IDE에서 실행이 불가할 수 있음에 주의하시기 바랍니다.
 */

#include <stdio.h>

int main()
{
	int amer, vala, hala;     // 순서대로 (음료) 아메리카노, 바닐라라떼, 한라봉에이드의 가격
	int amer_amount, vala_amount, hala_amount;     // 음료 항목들의 개수
	int drink, drink_amount;     // 순서대로 음료 항목들의 총 판매금액 합, 총 판매개수 합

	int blba, stca, chsa;     // 순서대로 (빵) 블루베리 베이글, 딸기 케이크, 치킨 샌드위치의 가격
	int blba_amount, stca_amount, chsa_amount;     // 빵 항목들의 개수
	int bread, bread_amount;     // 순서대로 빵 항목들의 총 매출, 총 판매개수

	int target;     // 목표 매출

	printf("============================= * ============================= \n");
	printf("안녕하세요. 예비 카페 창업주들을 위한 매출 계산 프로그램입니다. \n");
	printf("매출 예상에 쓰일 메뉴는 총 6개이며, 음료 3개와 빵 3개입니다. \n\n");
	printf(" [ 음료 메뉴판 ]                [ 빵 메뉴판 ] \n");
	printf(" 아메리카노                     블루베리 베이글 \n");
	printf(" 바닐라 라떼                    딸기 케이크 \n");
	printf(" 한라봉 에이드                  치킨 샌드위치 \n");
	printf("============================= * ============================= \n\n");

	printf("목표 매출은 얼마인가요? \n");
	scanf_s(" %d", &target);
	printf("이제 각 메뉴의 금액을 설정해주세요. \n");

	printf("\n아메리카노는 얼마에 판매할까요? (양의 정수만 입력, 최대 99,999원) \n");
	scanf_s(" %d", &amer);
	printf("\n바닐라 라떼는 얼마에 판매할까요? (양의 정수만 입력, 최대 99,999원) \n");
	scanf_s(" %d", &vala);
	printf("\n한라봉 에이드는 얼마에 판매할까요? (양의 정수만 입력, 최대 99,999원) \n");
	scanf_s(" %d", &hala);
	printf("\n블루베리 베이글은 얼마에 판매할까요? (양의 정수만 입력, 최대 99,999원) \n");
	scanf_s(" %d", &blba);
	printf("\n딸기 케이크는 얼마에 판매할까요? (양의 정수만 입력, 최대 99,999원) \n");
	scanf_s(" %d", &stca);
	printf("\n치킨 샌드위치는 얼마에 판매할까요? (양의 정수만 입력, 최대 99,999원) \n");
	scanf_s(" %d", &chsa);

	printf("\n설정하신 가격을 바탕으로 메뉴판을 완성했습니다. \n\n");
	printf("============================= * ============================= \n");
	printf(" [ 음료 메뉴판 ]                [ 빵 메뉴판 ] \n");
	printf(" 아메리카노     %5d원         블루베리 베이글  %5d원 \n", amer, blba);
	printf(" 바닐라 라떼    %5d원         딸기 케이크      %5d원 \n", vala, stca);
	printf(" 한라봉 에이드  %5d원         치킨 샌드위치    %5d원 \n", hala, chsa);
	printf("============================= * ============================= \n\n");

	printf("이제 예상되는 판매 개수를 설정해주세요. \n");

	printf("\n아메리카노는 몇 잔을 판매할까요? (양의 정수만 입력, 최대 9,999잔) \n");
	scanf_s(" %d", &amer_amount);
	printf("\n바닐라 라떼는 몇 잔을 판매할까요? (양의 정수만 입력, 최대 9,999잔) \n");
	scanf_s(" %d", &vala_amount);
	printf("\n한라봉 에이드는 몇 잔을 판매할까요? (양의 정수만 입력, 최대 9,999잔) \n");
	scanf_s(" %d", &hala_amount);
	printf("\n블루베리 베이글은 몇 개를 판매할까요? (양의 정수만 입력, 최대 9,999개) \n");
	scanf_s(" %d", &blba_amount);
	printf("\n딸기 케이크는 몇 개를 판매할까요? (양의 정수만 입력, 최대 9,999개) \n");
	scanf_s(" %d", &stca_amount);
	printf("\n치킨 샌드위치는 몇 개를 판매할까요? (양의 정수만 입력, 최대 9,999개) \n");
	scanf_s(" %d", &chsa_amount);

	drink_amount = amer_amount + vala_amount + hala_amount;
	drink = amer * amer_amount + vala * vala_amount + hala * hala_amount;

	bread_amount = blba_amount + stca_amount + chsa_amount;
	bread = blba * blba_amount + stca * stca_amount + chsa * chsa_amount;

	printf("\n\n\n\n설정하신 가격을 바탕으로 매출전표를 완성했습니다. \n\n");
	printf("======================= * ======================= \n");
	printf("[ 음료 매출 ] \n\n");
	printf("아메리카노       %5d원 * %4d잔 => %8d원 \n", amer, amer_amount, amer * amer_amount);
	printf("바닐라 라떼      %5d원 * %4d잔 => %8d원 \n", vala, vala_amount, vala * vala_amount);
	printf("한라봉 에이드    %5d원 * %4d잔 => %8d원 \n\n", hala, hala_amount, hala * hala_amount);
	printf("음료는 총 %d잔을 판매하였고, 한 메뉴당 평균 판매 잔수는 %.1lf잔입니다. \n", drink_amount, drink_amount / 3.0);
	printf("음료 매출은 총 %d원이고, 메뉴당 평균 매출은 약 %.1lf원입니다. \n\n", drink, drink / 3.0);

	printf("[ 빵 매출 ] \n\n");
	printf("블루베리 베이글  %5d원 * %4d개 => %8d원 \n", blba, blba_amount, blba * blba_amount);
	printf("딸기 케이크      %5d원 * %4d개 => %8d원 \n", stca, stca_amount, stca * stca_amount);
	printf("치킨 샌드위치    %5d원 * %4d개 => %8d원 \n\n", chsa, chsa_amount, chsa * chsa_amount);
	printf("빵은 총 %d개를 판매하였고, 한 메뉴당 평균 판매 개수는 %.1lf개입니다. \n", bread_amount, bread_amount / 3.0);
	printf("빵 매출은 총 %d원이고, 메뉴당 평균 매출은 약 %.1lf원입니다. \n\n", bread, bread / 3.0);

	printf("음료와 빵은 총 %d개를 판매하였고, 총 매출은 %d원입니다. \n", drink_amount + bread_amount, drink + bread);
	printf("======================= * ======================= \n\n");

	printf("목표 매출과 %9d원 만큼 차이납니다. \n", target - (drink + bread));
}
