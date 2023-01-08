#pragma once
#ifndef __CONFIG__H
#define __CONFIG__H

#include "Jtypedef.hpp"

#ifndef JSHMAX
    #define JSHMAX 680
#endif

#ifndef JSWMAX
    #define JSWMAX 1340
#endif

#ifndef JEDITABLE
    #define JEDITABLE JTRUE
#endif

#ifndef JAUTONS
    #define JAUTONS JTRUE
#endif

#define COLORINDEX0 {0  , 0  , 0  }
#define COLORINDEX1 {0  , 0  , 255}
#define COLORINDEX2 {0  , 255, 0  }
#define COLORINDEX3 {0  , 255, 255}
#define COLORINDEX4 {255, 0  , 0  }
#define COLORINDEX5 {255, 0  , 255}
#define COLORINDEX6 {255, 255, 0  }
#define COLORINDEX7 {192, 192, 192}
#define COLORINDEX8 {128, 128, 128}
#define COLORINDEX9 {0  , 0  , 128}
#define COLORINDEXA {0  , 128, 0  }
#define COLORINDEXB {0  , 128, 128}
#define COLORINDEXC {128, 0  , 0  }
#define COLORINDEXD {255, 224, 189}
#define COLORINDEXE {230, 145, 56 }
#define COLORINDEXF {255, 255, 255}


#endif