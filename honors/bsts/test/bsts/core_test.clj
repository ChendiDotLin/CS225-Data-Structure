(ns bsts.core-test
  (:use midje.sweet)
  (:use [bsts.core])
  (:import [bsts.core Node] ))

;; # The Tests

(defn list-to-tree
  "Takes a list of key elements and inserts them into a tree.
  The value will be a running counter of the elements inserted so far."
  [elts]
  (reduce #(add %1 (first %2) (second %2)) (make-tree) 
          (map #(vector %1 %2) elts (range 1 99999))))

(def balanced-tree (list-to-tree '(d b f a c e g)))
(def spindly-tree (list-to-tree '(g d f e c a b l k j m n o)))



(defn tree-to-list [node]
  (if (nil? node) nil
      (list (vector (:key node) (:value node))
            (tree-to-list (:left node))
            (tree-to-list (:right node)))))

(facts "Internal Tests"
       (fact "has a functioning tree-to-list"
             (tree-to-list balanced-tree) =>
             '([d 1] 
               ([b 2] ([a 4] nil nil)
                ([c 5] nil nil))
               ([f 3] ([e 6] nil nil)
                ([g 7] nil nil))) 

             (tree-to-list spindly-tree) =>
             '([g 1] ([d 2] ([c 5] ([a 6] nil ([b 7] nil nil)) nil) 
                      ([f 3] ([e 4] nil nil) nil))
               ([l 8] ([k 9] ([j 10] nil nil) nil)
                ([m 11] nil ([n 12] nil ([o 13] nil nil)))))))

(facts "Empty Trees"
       (fact "should have size zero."
             (size (make-tree)) => 0))

(facts "Adding elements changes size"
       (fact "Add one element makes size one"
             (size (add (make-tree) 10 10)) => 1 )
       (fact "Add seven elements makes size seven"
             (size balanced-tree) => 7 ))

(facts "Find"
       (fact "Does nothing with empty trees."
             (find (make-tree) 'x) => nil )
       (fact "Finds elements that are in the tree."
             (find balanced-tree 'd) => 1 
             (find balanced-tree 'b) => 2 
             (find balanced-tree 'f) => 3 
             (find balanced-tree 'g) => 7 
             (find balanced-tree 'e) => 6 
             (find balanced-tree 'c) => 5 
             (find balanced-tree 'a) => 4 )
       (fact "Doesn't find elements that aren't in the tree."
             (find balanced-tree 'x) => nil 
             (find balanced-tree 'aa) => nil ))

(facts "Delete"
       (fact "Does nothing to empty trees."
             (delete (make-tree) 'x) => (make-tree) )
       (fact "Deletes leaf nodes."
             (tree-to-list (delete balanced-tree 'a)) =>
             '([d 1] ([b 2] nil ([c 5] nil nil))
               ([f 3] ([e 6] nil nil) ([g 7] nil nil)))
             
             (tree-to-list (delete balanced-tree 'c)) =>
             '([d 1] ([b 2] ([a 4] nil nil) nil)
               ([f 3] ([e 6] nil nil) ([g 7] nil nil)))
             
             (tree-to-list (delete balanced-tree 'e)) =>
             '([d 1] ([b 2] ([a 4] nil nil) ([c 5] nil nil))
               ([f 3] nil ([g 7] nil nil)))
             
             (tree-to-list (delete balanced-tree 'g)) =>
             '([d 1] ([b 2] ([a 4] nil nil) ([c 5] nil nil))
               ([f 3] ([e 6] nil nil) nil)))

       (fact "Deletes one-child nodes."
             (comment ([g 1] ([d 2] ([c 5] ([a 6] nil ([b 7] nil nil)) nil) 
                              ([f 3] ([e 4] nil nil) nil))
                       ([l 8] ([k 9] ([j 10] nil nil) nil)
                        ([m 11] nil ([n 12] nil ([o 13] nil nil))))))

             (tree-to-list (delete spindly-tree 'f)) =>
             '([g 1] ([d 2] ([c 5] ([a 6] nil ([b 7] nil nil)) nil) 
                      ([e 4] nil nil))
               ([l 8] ([k 9] ([j 10] nil nil) nil)
                ([m 11] nil ([n 12] nil ([o 13] nil nil)))))

             (tree-to-list (delete spindly-tree 'k)) =>
             '([g 1] ([d 2] ([c 5] ([a 6] nil ([b 7] nil nil)) nil) 
                      ([f 3] ([e 4] nil nil) nil))
               ([l 8] ([j 10] nil nil)
                ([m 11] nil ([n 12] nil ([o 13] nil nil)))))
             
             (tree-to-list (delete spindly-tree 'n)) =>
             '([g 1] ([d 2] ([c 5] ([a 6] nil ([b 7] nil nil)) nil) 
                      ([f 3] ([e 4] nil nil) nil))
               ([l 8] ([k 9] ([j 10] nil nil) nil)
                ([m 11] nil ([o 13] nil nil)))))

       (fact "Deletes two-child nodes."
             (tree-to-list (delete spindly-tree 'd)) =>
             '([g 1] ([c 5] 
                      ([a 6] nil ([b 7] nil nil)) 
                      ([f 3] ([e 4] nil nil) nil))
               ([l 8] ([k 9] ([j 10] nil nil) nil)
                ([m 11] nil ([n 12] nil ([o 13] nil nil)))))
             
             (tree-to-list (delete spindly-tree 'l)) =>
             '([g 1] ([d 2] ([c 5] ([a 6] nil ([b 7] nil nil)) nil) 
                      ([f 3] ([e 4] nil nil) nil))
               ([k 9] ([j 10] nil nil) 
                ([m 11] nil ([n 12] nil ([o 13] nil nil)))))

             (tree-to-list (delete spindly-tree 'g)) =>
             '([f 3] ([d 2] ([c 5] ([a 6] nil ([b 7] nil nil)) nil) 
                      ([e 4] nil nil))
               ([l 8] ([k 9] ([j 10] nil nil) nil)
                ([m 11] nil ([n 12] nil ([o 13] nil nil)))))

             (tree-to-list (delete balanced-tree 'd)) =>
             '([c 5] 
               ([b 2] ([a 4] nil nil) nil)
               ([f 3] ([e 6] nil nil)
                ([g 7] nil nil)))))

