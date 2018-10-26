(ns adventure.core
  (:require '[[clojure.core.match :refer [match]]
              [clojure.string :as str]])
  (:gen-class))

(def the-map
  {:foyer {:desc "The walls are freshly painted but do not have
                 any pictures.  You get the feeling it was just
                 created for some game or something."
           :title "in the foyer"
           :dir {:north :hallway
                 :south :grue-pen }
           :content [:raw-egg]
           } 
   :grue-pen {:desc "There is a grue here.  You are about to get eaten."
              :title "the grue pen"
              :dir {}
              :content [:grue]}
   :hallway {:desc "It is very short, but not too short."
              :title "the hallway"
              :dir {:south :foyer
                    :north :kitchen }
              :content []}
   :kitchen {:desc "It looks like you could cook food here."
              :title "the kitchen"
              :dir {:south :hallway }
              :content []}

   })

(def adventurer
  {:location :foyer
   :inventory #{}
   :before #{}})

(defn status [adv]
  (let [location (adv :location)]
    (print (str "You are " (-> the-map location :title) ". " ))
    (when-not ((adv :before) location)
      (print (-> the-map location :desc) ) )
    (update-in adv [:before] #(conj % location))))

(defn go [dir adv]
  (let [curr-room (get-in adv [:location])]
   (if-let [dest (get-in the-map [curr-room :dir dir])]
     (assoc-in adv [:location] dest)
     (foo 123)
     (println "You cannot go that direction.")) ))

(defn respond [inst adv]
  (match inst
         [:north] (go :north adv)
         _ (do 
             (println "I'm sorry Dave.  I cannot allow you to do that.")
             adv) ) )

(defn to-keywords [st]
   (mapv keyword (str/split st #" +")))

(defn -main
  [& args]
  (println "Welcome to the Uncooked Egg Adventure!")
  (loop [the-m the-map
         the-a adventurer]
    (let [the-a' (status the-a)
          _      (println "What do you want to do?")
          inst   (read-line) ]
      (recur the-m (respond (to-keywords inst) the-a'))
      ) ) )
