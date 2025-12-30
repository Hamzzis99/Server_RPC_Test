// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ArenaBattleTarget : TargetRules
{
    public ArenaBattleTarget( TargetInfo Target) : base(Target)
    {
        Type = TargetType.Game;
        
        // 5.x 버전대에서는 보통 V5를 유지하지만, 
        // 최신 기능을 강제하려면 BuildSettingsVersion.Latest를 사용할 수도 있습니다.
        DefaultBuildSettings = BuildSettingsVersion.V6;

        // 여기를 5.7로 변경합니다.
        // 주의: 설치된 엔진이 5.7 버전(혹은 Main 브랜치)이어야 컴파일 에러가 나지 않습니다.
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_7;

        ExtraModuleNames.Add("ArenaBattle");
    }
}