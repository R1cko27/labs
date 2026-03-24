#include "study_group.h"

int main() {
    StudyGroup group1, group2, g1, g2, g3, g4;
    ErrorCode err;
    
    // Инициализация, копирование, изменения названия группы
    init_study_group(&group1, "AB-420", IS, 2024, B);
    init_study_group(&group2, "AP-527", PI, 2025, M);
    
    copy_study_group(&group2, &group1);
    set_group_name(&group1, "ABC-420");
    
    print_study_group(&group1);

    // Динамическая память
    StudyGroup* dynamic_group1 = create_study_group("AP-526", PI, 2025, B);
    StudyGroup* dynamic_group2 = create_study_group("AVT-512", VT, 2025, M);
    
    copy_study_group(dynamic_group2, dynamic_group1);
    
    print_study_group(dynamic_group2);
    return 0;
}