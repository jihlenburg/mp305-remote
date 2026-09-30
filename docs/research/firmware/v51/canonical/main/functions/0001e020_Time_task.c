/* Address: 0001e020; name: Time_task; body bytes: 146 */

/* Confirmed by task-create function pointer and literal name Time_task. */

void Time_task(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  iVar5 = 0;
  iVar1 = FUN_0001c358();
  iVar3 = 0;
  iVar6 = iVar1;
  do {
    FUN_000658d4(10);
    if (iVar5 == 0) {
      iVar5 = FUN_00012bec(10);
    }
    FUN_0001920c(10);
    FUN_00018728(10);
    FUN_00011c18(10);
    FUN_00011eac(10);
    FUN_0001227c();
    FUN_0001a3b0(10);
    iVar2 = FUN_0001c358();
    FUN_0001ab34(iVar2 - iVar1);
    iVar4 = iVar3 + 1;
    iVar1 = iVar2;
    switch(iVar3) {
    case 0:
      iVar2 = FUN_0001c358();
      FUN_00019a50(iVar2 - iVar6);
      iVar3 = iVar4;
      iVar6 = iVar2;
      break;
    case 1:
      FUN_0001a660();
      iVar3 = iVar4;
      break;
    case 2:
      FUN_000193c0(100);
      iVar3 = iVar4;
      break;
    case 3:
    case 4:
    case 5:
    case 8:
      iVar3 = iVar4;
      break;
    case 6:
      FUN_000125c0();
      iVar3 = iVar4;
      break;
    case 7:
      FUN_00019fe0(100);
      iVar3 = iVar4;
      break;
    default:
      FUN_000181f8(100);
      iVar3 = 0;
    }
  } while( true );
}

