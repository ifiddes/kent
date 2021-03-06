table llaInfo
"Extra information for a lowe lab array"
    (
    string name;    "Name of primer pair"
    string type;    "Type of primer pair (ORF or intergenic)"
    float SnTm;     "Sense primer annealing temp"
    float SnGc;     "Sense primer annealing temp"
    float SnSc;     "Sense primer self-complementarity score"
    float Sn3pSc;   "Sense primer 3-prime self-complementarity score"
    float AsnTm;    "Antisense primer annealing temp"
    float AsnGc;    "Antisense primer annealing temp"
    float AsnSc;    "Antisense primer self-complementarity score"
    float Asn3pSc;  "Antisense primer 3-prime self-complementarity score"
    uint prodLen;   "PCR product length"
    uint ORFLen;    "Source ORF length"
    float meltTm;   "PCR melting temperature"
    float frcc;     "Forward+reverse primer cross complementarity"
    float fr3pcc;   "3-prime forward+reverse primer cross complementarity"
    lstring SnSeq;  "Sense primer sequence"
    lstring AsnSeq; "Antisense primer sequence"
    uint numCorrs;  "Number of correlations stored"
    string[numCorrs] corrNames; "Names of correlated genes"
    float[numCorrs] corrs;  "Correlations"
    )
