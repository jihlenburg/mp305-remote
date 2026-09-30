/* Address: 00022058; name: FUN_00022058; body bytes: 618 */

void FUN_00022058(undefined4 param_1)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  DAT_1ffe029c = DAT_1ffe029c + 1;
  if (199 < DAT_1ffe0298) {
    uVar1 = 0;
    do {
      (&DAT_1fffacc0)[uVar1] = (&DAT_1fffacc4)[uVar1];
      (&DAT_1fffafe0)[uVar1] = (&DAT_1fffafe4)[uVar1];
      (&DAT_1fffb300)[uVar1] = (&DAT_1fffb304)[uVar1];
      uVar1 = uVar1 + 1 & 0xff;
    } while (uVar1 < 199);
    uVar2 = FUN_00052960(param_1);
    FUN_0003f9a4(uVar2,DAT_1ffe0338,&DAT_1fffacc0);
    uVar2 = FUN_00052960(param_1);
    FUN_0003f9a4(uVar2,DAT_1ffe033c,&DAT_1fffafe0);
    DAT_1ffe0298 = 199;
  }
  iVar3 = DAT_1ffe0298;
  (&DAT_1fffacc0)[DAT_1ffe0298] = (uint)DAT_1fffab7a;
  (&DAT_1fffafe0)[iVar3] = (uint)DAT_1fffab78;
  (&DAT_1fffb300)[iVar3] = DAT_1fffab9c;
  if (iVar3 < 200) {
    uVar2 = FUN_00052960(param_1);
    FUN_0003fa78(uVar2,DAT_1ffe0338,DAT_1ffe0298,(&DAT_1fffacc0)[DAT_1ffe0298]);
    uVar2 = FUN_00052960(param_1);
    FUN_0003fa78(uVar2,DAT_1ffe033c,DAT_1ffe0298,(&DAT_1fffafe0)[DAT_1ffe0298]);
  }
  FUN_00052960(param_1);
  thunk_FUN_0004d3d8();
  DAT_1ffe0298 = DAT_1ffe0298 + 1;
  if (DAT_1fffabc0 != -1) {
    if (DAT_1fffabc0 < DAT_1ffe029c) {
      iVar3 = FUN_0003f91a(DAT_1ffe053c,DAT_1ffe033c);
      iVar5 = *(int *)(iVar3 + DAT_1fffabc0 * 4);
      iVar3 = FUN_0003f91a(DAT_1ffe053c,DAT_1ffe0338);
      uVar1 = (*(int *)(iVar3 + DAT_1fffabc0 * 4) * iVar5) / 10000;
      iVar3 = FUN_0003f91a(DAT_1ffe053c,DAT_1ffe033c);
      iVar5 = *(int *)(iVar3 + DAT_1fffabc0 * 4);
      iVar3 = FUN_0003f91a(DAT_1ffe053c,DAT_1ffe033c);
      iVar3 = *(int *)(iVar3 + DAT_1fffabc0 * 4);
      uVar2 = FUN_0004b9de(DAT_1ffe053c,0);
      uVar2 = FUN_0004b9de(uVar2,0);
      FUN_000499de(uVar2,"V-%02d.%02dV",iVar3 / 100,iVar5 % 100);
      iVar3 = FUN_0003f91a(DAT_1ffe053c,DAT_1ffe0338);
      iVar3 = *(int *)(iVar3 + DAT_1fffabc0 * 4);
      iVar5 = FUN_0003f91a(DAT_1ffe053c,DAT_1ffe0338);
      iVar5 = *(int *)(iVar5 + DAT_1fffabc0 * 4);
      uVar2 = FUN_0004b9de(DAT_1ffe053c,0);
      uVar2 = FUN_0004b9de(uVar2,1);
      FUN_000499de(uVar2,"I-%d.%03dA",iVar5 / 1000,iVar3 % 1000);
      uVar2 = FUN_0004b9de(DAT_1ffe053c,0);
      uVar2 = FUN_0004b9de(uVar2,2);
      FUN_000499de(uVar2,"P-%03d.%01dW",uVar1 / 10,uVar1 % 10);
      iVar5 = (&DAT_1fffb300)[DAT_1fffabc0];
      iVar4 = (iVar5 % 0xe10) % 0x3c;
      iVar3 = iVar5 / 0xe10;
      iVar5 = (iVar5 % 0xe10) / 0x3c;
      uVar2 = FUN_0004b9de(DAT_1ffe053c,0);
      uVar2 = FUN_0004b9de(uVar2,3);
    }
    else {
      uVar2 = FUN_0004b9de(DAT_1ffe053c,0);
      uVar2 = FUN_0004b9de(uVar2,0);
      FUN_000499de(uVar2,"V-%02d.%02dV",0);
      uVar2 = FUN_0004b9de(DAT_1ffe053c,0);
      uVar2 = FUN_0004b9de(uVar2,1);
      FUN_000499de(uVar2,"I-%d.%03dA",0);
      uVar2 = FUN_0004b9de(DAT_1ffe053c,0);
      uVar2 = FUN_0004b9de(uVar2,2);
      FUN_000499de(uVar2,"P-%03d.%01dW",0);
      uVar2 = FUN_0004b9de(DAT_1ffe053c,0);
      uVar2 = FUN_0004b9de(uVar2,3);
      iVar5 = 0;
      iVar3 = 0;
      iVar4 = 0;
    }
    FUN_000499de(uVar2,"T-%ld:%02ld:%02ld",iVar3,iVar5,iVar4);
  }
  return;
}

