/*  ___ _  ___ _ _                                                                                                    *\
 * / __| |/ (_) | |     Your SKilL cpp Binding                                                                        * 
 * \__ \ ' <| | | |__   <<debug>>                                                                                     * 
 * |___/_|\_\_|_|____|  by: <<some developer>>                                                                        * 
\*                                                                                                                    */
#include <skill/api/String.h>
#include <skill/internal/StringPool.h>

namespace empty {

    /**
     * holds instances of all strings
     */
    struct StringKeeper : public ::skill::internal::AbstractStringKeeper {
    };
}
